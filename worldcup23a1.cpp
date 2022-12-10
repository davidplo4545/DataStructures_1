#include "worldcup23a1.h"
world_cup_t::world_cup_t()
{
    m_totalPlayersNum = 0;
    m_teamsNum = 0;
    m_validTeamsNum=0;
    m_playersTree = new AVLTree<int,Player*>();
    m_rankedPlayersTree = new AVLTree<Player,Player*>();
    m_teamsTree = new AVLTree<int,Team*>();
    m_validTeamsTree = new AVLTree<int,Team*>();
}

world_cup_t::~world_cup_t()
{
    m_teamsTree->deleteEntireTreeData();
    m_playersTree->deleteEntireTreeData();
    delete m_rankedPlayersTree;
    delete m_validTeamsTree;
    delete m_teamsTree;
    delete m_playersTree;
}

StatusType world_cup_t::add_team(int teamId, int points)
{
    TreeNode<int, Team*>* teamNode = m_teamsTree->find(teamId);
    if(teamNode != nullptr)
        return StatusType::FAILURE;
    try{
        Team* newTeam = new Team(teamId, points);
        m_teamsTree->insert(teamId, newTeam);
        m_teamsNum +=1;
    }
    catch(InvalidInput &e)
    {
        return StatusType::INVALID_INPUT; //
    }
    catch(std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    return StatusType::SUCCESS;

}


StatusType world_cup_t::remove_team(int teamId)
{
    Team* team = nullptr;
    if(teamId <= 0 )
        return StatusType::INVALID_INPUT;
    TreeNode<int,Team*>* teamNodeToDelete = m_teamsTree->find(teamId);
    if(teamNodeToDelete == nullptr || !(teamNodeToDelete->m_data->canBeDeleted()))
    {
        return StatusType::FAILURE;

    }
    else
    {
        team = teamNodeToDelete->m_data;
        if(teamNodeToDelete->m_data->isInRanked())
        {
            m_validTeamsTree->deleteByKey(teamId);
            m_validTeamsNum -=1;
        }
        m_teamsTree->deleteByKey(teamId);

        m_teamsNum -=1;
    }
    delete team;

    return StatusType::SUCCESS;
}
StatusType world_cup_t::add_player(int playerId, int teamId, int gamesPlayed,
                                   int goals, int cards, bool goalKeeper) {

    TreeNode<int, Player *> *isFoundNode = m_playersTree->find(playerId);
    TreeNode<int, Team *> *isFoundTeam = m_teamsTree->find(teamId);
    bool bad_inputs ((playerId <= 0 || teamId <= 0 || gamesPlayed < 0 || goals < 0 || cards < 0) || (gamesPlayed == 0 && (goals > 0 || cards > 0)));

    if(!bad_inputs)
        if (isFoundNode != nullptr || isFoundTeam == nullptr)
        {
            return StatusType::FAILURE;
        }

    try{
        Player *newPlayer = new Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper);
        m_playersTree->insert(playerId, newPlayer);
        TreeNode<Player, Player *> *rankNode;
        rankNode = m_rankedPlayersTree->insert(*newPlayer, newPlayer);
        newPlayer->setRankNode(rankNode);
        TreeNode<int, Team *> *teamNode = m_teamsTree->find(teamId);
        Team *team = teamNode->m_data;
        team->addPlayer(newPlayer);

        if (team->isAbleToPlay() && !(team->isInRanked())) {
            m_validTeamsTree->insert(teamId, team);
            team->setIsInRanked(true);
            m_validTeamsNum += 1;
        }
        newPlayer->setTeam(team);
        newPlayer->updateGamesPlayedByFactor(team->getGamesPlayed());
        m_totalPlayersNum += 1;
    }
    catch (InvalidInput &e) {
        return StatusType::INVALID_INPUT; //
    }
    catch (std::bad_alloc &e) {
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}



StatusType world_cup_t::remove_player(int playerId)
{
    Team* team;
    Player* player;
    if(playerId <= 0)
        return StatusType::INVALID_INPUT;
    try{
        try{
            TreeNode<int,Player*>* playerNode = m_playersTree->find(playerId);
            if(playerNode == nullptr)
            {
                return StatusType::FAILURE;
            }
            player = playerNode->m_data;
            team = player->getTeam();

            m_playersTree->deleteByKey(playerId);
            bool hasDataChanged = false;
            TreeNode<Player,Player*>* newNode = m_rankedPlayersTree->deleteByKey(*player, &hasDataChanged);
            if(hasDataChanged)
                newNode->m_data->setRankNode(newNode);
        }
        catch(FailureError &f){
            return StatusType::FAILURE;
        }
        try{
            team->removePlayer(player);

            if(!team->isAbleToPlay() && team->isInRanked())
            {
                m_validTeamsTree->deleteByKey(team->getId());
                team->setIsInRanked(false);
            }
            m_totalPlayersNum-=1;
        }
        catch(FailureError &f)
        {
            return StatusType::FAILURE;

        }
    }
    catch(FailureError &e)
    {
        return StatusType::FAILURE;
    }

    delete player;
    return StatusType::SUCCESS;
}

StatusType world_cup_t::update_player_stats(int playerId, int gamesPlayed,
                                            int scoredGoals, int cardsReceived)
{
    if(playerId <= 0 || gamesPlayed < 0 || scoredGoals < 0 || cardsReceived < 0)
        return StatusType::INVALID_INPUT;
    try{
        TreeNode<int,Player*>* playerNode = m_playersTree->find(playerId);
        if(!playerNode) return StatusType::FAILURE;
        Player* player = playerNode->m_data;
        Team* team = player->getTeam();
        // Delete and Add a new node with the new stats to both trees, the
        // general one and the team one.
        bool hasDataChanged = false;
        TreeNode<Player,Player*>* newNode = m_rankedPlayersTree->deleteByKey(*player, &hasDataChanged);
        if(hasDataChanged)
            newNode->m_data->setRankNode(newNode);

        team->removePlayerFromRanked(player);
        player->updateStats(gamesPlayed, scoredGoals, cardsReceived);
        team->updateStrength(scoredGoals, cardsReceived);

        try{
            TreeNode<Player,Player*>* rankNode =m_rankedPlayersTree->insert(*player, player);
            team->addPlayerToRanked(player);
            player->setRankNode(rankNode);
        }
        catch(FailureError &e){
            return StatusType::FAILURE;
        }
    }
    catch(FailureError &e)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::play_match(int teamId1, int teamId2)
{
    if(teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;
    TreeNode<int, Team*>*  teamNode1= m_teamsTree->find(teamId1);
    TreeNode<int, Team*>*  teamNode2= m_teamsTree->find(teamId2);
    if(!teamNode1 || !teamNode2) return StatusType::FAILURE;
    Team* team1 = teamNode1->m_data;
    Team* team2 = teamNode2->m_data;
    if(!team1->isAbleToPlay() || !team2->isAbleToPlay()) return StatusType::FAILURE;

    if(team1->getStrength() > team2->getStrength())
    {
        team1->updatePointsAfterGame(3);
        team2->updatePointsAfterGame(0);
    }
    else if(team1->getStrength() < team2->getStrength())
    {
        team1->updatePointsAfterGame(0);
        team2->updatePointsAfterGame(3);
    }
    else
    {
        team1->updatePointsAfterGame(1);
        team2->updatePointsAfterGame(1);
    }
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_num_played_games(int playerId)
{
    if(playerId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);
    TreeNode<int, Player*>*  playerNode= m_playersTree->find(playerId);
    if(!playerNode) return output_t<int>(StatusType::FAILURE);
    Player* player = playerNode->m_data;

    Team* team = player->getTeam();
    return output_t<int>(player->getGamesPlayed() + team->getGamesPlayed());
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if(teamId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);
    TreeNode<int, Team*>*  teamNode= m_teamsTree->find(teamId);
    if(!teamNode) return output_t<int>(StatusType::FAILURE);
    Team* team = teamNode->m_data;
    return output_t<int>(team->getPoints());

}

void world_cup_t::forceRemoveTeam(int id, Team* team)
{
    team->changeShouldBeDeleted();
    team->resetPlayersCount();
    remove_team(id);
}

StatusType world_cup_t::unite_teams(int teamId1, int teamId2, int newTeamId)
{
    if(teamId1 <= 0 || teamId2 <= 0 || newTeamId <=0 || teamId1 == teamId2)
        return StatusType::INVALID_INPUT;
    TreeNode<int, Team*>*  teamNode1= m_teamsTree->find(teamId1);
    TreeNode<int, Team*>*  teamNode2= m_teamsTree->find(teamId2);
    TreeNode<int, Team*>*  newTeamNode= m_teamsTree->find(newTeamId);
    if(!teamNode1 || !teamNode2 || (newTeamNode!=nullptr && (newTeamId != teamId1 && newTeamId != teamId2))) return StatusType::FAILURE;
    Team* team1 = teamNode1->m_data;
    Team* team2 = teamNode2->m_data;

    TreeNode<int,Player*>** playersArr1 = new TreeNode<int,Player*>*[team1->getPlayersCount()];
    TreeNode<int,Player*>** playersArr2 = new TreeNode<int,Player*>*[team2->getPlayersCount()];
    TreeNode<int,Player*>** playersArrNew = new TreeNode<int,Player*>*[team1->getPlayersCount() + team2->getPlayersCount()];

    TreeNode<Player,Player*>** playersRankedArr1 = new  TreeNode<Player,Player*>*[team1->getPlayersCount()];
    TreeNode<Player,Player*>** playersRankedArr2 = new TreeNode<Player,Player*>*[team2->getPlayersCount()];
    TreeNode<Player,Player*>** rankedPlayersArrNew = new TreeNode<Player,Player*>*[team1->getPlayersCount() + team2->getPlayersCount()];
    team1->getSortedPlayersArray(playersArr1, playersRankedArr1);
    team2->getSortedPlayersArray(playersArr2 ,playersRankedArr2);
    // merge both arrays into one
    merge(playersArr1, team1->getPlayersCount(), playersArr2, team2->getPlayersCount(), playersArrNew);
    merge(playersRankedArr1, team1->getPlayersCount(), playersRankedArr2, team2->getPlayersCount(), rankedPlayersArrNew);
    Team* newTeam = new Team(newTeamId, team1->getPoints()+team2->getPoints());
    newTeam->updateStatsFromTeams(team1,team2);

    newTeam->createPlayerTrees(playersArrNew, rankedPlayersArrNew);
    forceRemoveTeam(teamId1, team1);
    forceRemoveTeam(teamId2, team2);
    try{
        m_teamsTree->insert(newTeamId, newTeam);
        m_teamsNum +=1;

        // Check if valid for playing matches
        if(newTeam->isAbleToPlay() && !newTeam->isInRanked())
        {
            m_validTeamsNum +=1;
            newTeam->setIsInRanked(true);
            m_validTeamsTree->insert(newTeamId, newTeam); // here it gets stuck
        }
    }
    catch(AllocationError &e){
        delete newTeam;
        return StatusType::ALLOCATION_ERROR;
    }
    catch(FailureError &e)
    {
        delete newTeam;
        return StatusType::FAILURE;
    }
    delete []playersArr1;
    delete []playersArr2;
    delete []playersArrNew;
    delete []playersRankedArr1;
    delete []playersRankedArr2;
    delete []rankedPlayersArrNew;
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_top_scorer(int teamId)
{
    if(teamId == 0) return output_t<int>(StatusType::INVALID_INPUT);
    TreeNode<Player, Player*>* topNode;
    if(teamId < 0)
    {
        topNode = m_rankedPlayersTree->getTopNode();
    }
    else{
        TreeNode<int, Team*>*  teamNode= m_teamsTree->find(teamId);
        if(!teamNode) return output_t<int>(StatusType::FAILURE);
        Team* team = teamNode->m_data;
        topNode = team->getRankedTopNode();

    }

    if(topNode == nullptr) return output_t<int>(StatusType::FAILURE);
    return output_t<int>(topNode->m_data->getId());
}

output_t<int> world_cup_t::get_all_players_count(int teamId)
{
    if(teamId == 0)
        return output_t<int>(StatusType::INVALID_INPUT);
    if(teamId < 0)
        return m_totalPlayersNum;

    TreeNode<int, Team*>*  teamNode= m_teamsTree->find(teamId);
    if(!teamNode) return output_t<int>(StatusType::FAILURE);
    Team* team = teamNode->m_data;
    return output_t<int>(team->getPlayersCount());
}

StatusType world_cup_t::get_all_players(int teamId, int *const output)
{
    if(teamId == 0 || output == nullptr) return StatusType::INVALID_INPUT;
    int count=m_totalPlayersNum;
    TreeNode<Player, Player*>* topNode;
    if(teamId < 0)
    {
        topNode = m_rankedPlayersTree->getTopNode();
    }
    else{
        TreeNode<int, Team*>*  teamNode= m_teamsTree->find(teamId);
        if(!teamNode) return StatusType::FAILURE;
        Team* team = teamNode->m_data;
        count = team->getPlayersCount();
        topNode = team->getRankedTopNode();

    }

    if(topNode == nullptr) return StatusType::FAILURE;
    int i=count-1;
    while(topNode != nullptr)
    {
        try{
            output[i] = topNode->m_data->getId();
        }
        catch(std::exception &e)
        {
            return StatusType::ALLOCATION_ERROR;
        }
        i--;
        topNode = topNode->m_closeBelow;
    }
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_closest_player(int playerId, int teamId)
{

    if(teamId <= 0 || playerId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);
    TreeNode<int, Team*>*  teamNode= m_teamsTree->find(teamId);

    if(!teamNode)
    {
        return output_t<int>(StatusType::FAILURE);
    }

    Team* team = teamNode->m_data;
    Player* closestPlayer = team->getClosestPlayer(playerId);

    if(closestPlayer == nullptr) return output_t<int>(StatusType::FAILURE);
    return output_t<int>(closestPlayer->getId());
}

output_t<int> world_cup_t::knockout_winner(int minTeamId, int maxTeamId)
{
    if(minTeamId<0 || maxTeamId <0 || minTeamId > maxTeamId)
        return output_t<int>(StatusType::INVALID_INPUT);
    TreeNode<int,Team*>* currNode = m_validTeamsTree->findClosestToMinNode(minTeamId);
    if(currNode == nullptr) return output_t<int>(StatusType::FAILURE);
    Team* teamMin = currNode->m_data;
    if(teamMin->getId() > maxTeamId || teamMin->getId() < minTeamId || (teamMin->getId() == maxTeamId && !(teamMin->isInRanked())))
    {
        return output_t<int>(StatusType::FAILURE);
    }

    Team** tempValidTeams = new Team*[m_validTeamsNum];

//    TreeNode<int,Team*>* currNode = m_validTeamsTree->getTopNode();
    int currSize=0;
    while(currNode!=nullptr && currNode->m_key <= maxTeamId && currSize < m_validTeamsNum) // added currSize < m_validTeamsNum
    {
        if(currNode->m_key <= maxTeamId)
        {
            tempValidTeams[currSize] = new Team (*(currNode->m_data));
            currSize++;
        }
        currNode = currNode->m_closeAbove;
    }

    if(currSize ==0) {
        for (int i = 0; i < currSize; ++i) {
            delete tempValidTeams[i];
        }
        delete [] tempValidTeams;
        return output_t<int>(StatusType::FAILURE);
    }
    Team** validTeams = new Team*[currSize];
    // reversing the array (from low to high)
    for(int j=0;j<currSize;j++)
    {
        validTeams[j] = tempValidTeams[j];
    }

    int mult = 1;
    // play the game
    while(true)
    {
        for(int curr=0;curr<currSize;curr+=mult*2)
        {
            if(curr+mult >= currSize) break;
            validTeams[curr] = validTeams[curr]->playMatch(validTeams[curr+mult]);
        }
        mult *=2;
        if(mult >= currSize) break;
    }
    int result = validTeams[0]->getId();
    for (int i = 0; i < currSize; ++i) {
        delete tempValidTeams[i];
    }
    delete []validTeams; // CHECK IN AMIR TEST
    delete []tempValidTeams;

    return output_t<int>(result);
}