void zoneInfo(){
    game.getZone(zoneData);
    //for(int i = 0; i < 3; i++, ourZone[i] = zoneData[i], theirZone[i] = -zoneData[i]);      //some memory more
    assign(ourZone, zoneData[0], zoneData[1], zoneData[2]);
    assign(theirZone, zoneData[0]*(-1), zoneData[1]*(-1), zoneData[2]*(-1));
}

/*we get the location of our and their zone*/


bool packIsMoving(int id){
    game.getItemZRState(itemState, targetNumber);
    return(itemState[3] != 0.00 || itemState[4] != 0.00 || itemState[5] != 0.00);
}

bool packInTheirZone(int id){
    float temp[3];
    game.getItemLoc(temp, id);
    return(compareVector(temp, theirZone, 0.08));
}

/*we check if a pack is in their zone or not*/

void getMyPos() {
    api.getMyZRState(myState);
    //for(int i = 0; i < 3; i++, myPos[i] = myState[i]);
    copyArray(myState, myPos, 0, 3);
}

/*we get our position*/


bool packInZone(){
    float temp[3];
    game.getItemLoc(temp, targetNumber);
    return(compareVector(temp, ourZone, 0.05));
}

void calcPoint(){
    game.getItemZRState(itemState, targetNumber);
    if(itemState[3] <= 0.1 && itemState[4] <= 0.1 && itemState[5] <= 0.1){
        game.getItemLoc(actualTarget, targetNumber);
        for(int i=0; i<3; i++){
            itemAtt[i] = itemState[i+6];
            pointAtt[i] = -itemAtt[i];
        }
        mathVecNormalize(itemAtt, 3);
        float length = mathVecMagnitude(itemAtt, 3);
        for(int i=0; i<3; i++)
            virtualTarget[i] = itemAtt[i] * distFromTarget/length*0.99 + actualTarget[i];
        calculated = true;
    }
}

/*this function calculates the docking point based on the position, attitude and type of item*/

bool rightSpeed(){
    float myVel[3];
    for(int i=0; i < 3; ++i)
            myVel[i] = myState[i+3];
    return(mathVecMagnitude(myVel, 3) < 0.01);
}