void worthyPack() {
    for(int i = 0; i < 4; i++) {
        getRank(i);
    }
    getWorthyPackInfo();
    setDist();
}

/*cumulative function to learn which pack is the worthiest*/

int itemStat(int num) {
    if(game.itemInZone(num))
        return 3;

    if(packInTheirZone(num) && game.hasItem(num) == 0)
        return 4;

    return(game.hasItem(num));
}

/* we check if the pack is in our or their zone to calculate the real rating of the item*/

void getRank(int num) {
    game.getItemZRState(itemState, num);
    float target[3];
    getMyPos();
    game.getItemLoc(target, num);
    ranking[num] = 1/(((dist(myPos, target)*dist(myPos, target))));
    switch(num){
        case 0:   //large
        case 1:
            ranking[num]*=2.0;
            break;
        case 2:   //medium
        case 3:
            ranking[num]*=1.5;
            break;
    }
    switch(itemStat(num)){
        case 0:
            ranking[num]*=1;
            break;
        case 4:
            ranking[num]*=1.75;
            break;
        default:
            ranking[num]*=-100;
            break;
    }
    if(dist(target, theirPos) < 0.2 && packInTheirZone(num))
        ranking[num]*=-1;
    if(itemState[3] > 0.1 || itemState[4] > 0.1 || itemState[5] > 0.1)
        ranking[num]*=-1;
}

/* the rating is based on distance and points/second that the item gives*/

void getWorthyPackInfo(){
    targetNumber = 0;
    float max = ranking[0];
    for(int i = 0; i < 4; i++){
        if(ranking[i] > max){
            targetNumber = i;
            max = ranking[i];
        }
    }
    game.getItemLoc(actualTarget, targetNumber);
}

/*calculates the max valued pack */

void setDist(){
    switch(targetNumber){
        case 0:
        case 1:
            //distFromTarget = .182;
            distFromTarget = .162;
            distMin = 0.151;
            distMax = 0.173;
            break;
        case 2:
        case 3:
            //distFromTarget = .1725;
            distFromTarget = .143;
            distMin = 0.138;
            distMax = 0.160;
            break;
    }
}

/*set docking distances based on pack. (probably useless with the new functions we're using) */
