void worthyPack() {
    for(int i = 0; i < 4; i++) {
        getRank(i);
    }
    getWorthyPackInfo();
    setDist();
}

/*cumulative function to learn which pack is the worthiest*/


void getRank(int num) {
    game.getItemZRState(itemState, num);
    float target[3];
    getMyPos();
    game.getItemLoc(target, num);
    ranking[num] = 1/(((dist(myPos, target)*dist(myPos, target))));
    if(num == 0 || num == 1)
            ranking[num]*= 1.7;
    if(packInZone(targetNumber))
        ranking[num] = NULL;
    game.getItemZRState(itemState, num);
    if(packIsMoving(num)){
        ranking[num] = NULL;
    }
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
            distFromTarget = .162;
            distMin = 0.151;
            distMax = 0.173;
            break;
        case 2:
        case 3:
            distFromTarget = .143;
            distMin = 0.138;
            distMax = 0.160;
            break;
    }
}

/*set docking distances based on pack. (probably useless with the new functions we're using) */