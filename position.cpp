char ourColor(){
    getMyPos();
    if(myPos[1] > 0)
        return 'B';
    else
        return 'R';
}

/*we learn our color. Is it relevant in alliance?*/

void zoneInfo(){
    float zoneData[4];
    game.getZone(zoneData);
    assign(ourZone, zoneData[0], zoneData[1], zoneData[2]);
    assign(theirZone, zoneData[0]*(-1), zoneData[1]*(-1), zoneData[2]*(-1));
}

/*we get the location of our and their zone*/

bool packInZone(){
    float temp[3];
    game.getItemLoc(temp, targetNumber);
    if(compareVector(temp, ourZone, 0.05))
        return true;
    else 
        return false; 
}

/*we check if a pack is in our zone or not*/

bool packInTheirZone(int id){
    float temp[3];
    game.getItemLoc(temp, id);
    if(compareVector(temp, theirZone, 0.08))
        return true;
    else
        return false;
}

bool packIsMoving(int id){
    game.getItemZRState(itemState, id);
    return(itemState[3] != 0.00 || itemState[4] != 0.00 || itemState[5] != 0.00);
}

/*we check if a pack is in their zone or not*/

void getMyPos() {
    api.getMyZRState(myState);
    for(int i = 0; i < 3; i++, myPos[i] = myState[i]);
}

/*we get our position*/

void getTheirPos(){
    api.getMyZRState(myState);
    for(int i = 0; i < 3; i++, theirPos[i] = myState[i]);
}