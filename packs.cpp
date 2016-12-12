//calculates the worthiest pack to go for

void worthyPack() {
    for(int i = 0; i < 4; i++) {    //we ignore small packs, not worth at all
        getRank(i);
    }
    getWorthyPackInfo();
    setDist();
}


//details about position of the pack

int itemStat(int num) {
    if(game.itemInZone(num))  //in our zone
        return 3;

    if(packInTheirZone(num) && game.hasItem(num) == 0)  //in their zone
        return 4;

    return(game.hasItem(num));  //otherwise,
}


//get rating for each pack based on their status
void getRank(int num) {
    float target[3];
    getMyPos();
    game.getItemLoc(target, num);
    ranking[num] = 1/(dist(myPos, target)); //the closer it is, the worthier it gets
    switch(num){
        case 0:   //large
        case 1:
            ranking[num]*=4.5;
            break;
        case 2:   //medium
        case 3:
            ranking[num]*=2.5;
            break;
    }
    switch(itemStat(num)){
        case 0:
            ranking[num]*=1;  //no special case
            break;
        case 4:
            ranking[num]*=1.75; //in their zone
            break;
        default:
            ranking[num]*=-100; //don't even consider that pack
            break;
    }
}


//processes info about packs, determining the worthiest to go for
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


//set distances for docks based on our target
void setDist(){
    switch(targetNumber){
        case 0:   //large
        case 1:
            distFromTarget = .182;   //medium distance
            distMin = 0.151;
            distMax = 0.173;  
            break;
        case 2: //medium
        case 3:
            distFromTarget = .1725;
            distMin = 0.138;
            distMax = 0.160;
            break;
    }
}
