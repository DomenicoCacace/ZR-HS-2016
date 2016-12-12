//returns R or B based on our color

char ourColor(){
    getMyPos();
    if(myPos[1] > 0)
        return 'B';
    else
        return 'R';
}

//gets info about assembly zones coordinates

void zoneInfo(){
    float zoneData[4];
    game.getZone(zoneData);
    assign(ourZone, zoneData[0], zoneData[1], zoneData[2]);
    assign(theirZone, zoneData[0]*(-1), zoneData[1]*(-1), zoneData[2]*(-1));
}


//check if a pack is into our zone

bool packInZone(){
    float temp[3];
    game.getItemLoc(temp, targetNumber);
    if(compareVector(temp, ourZone, 0.05))
        return true;
    else
        return false;
}


//check if a pack is into opponents' zone

bool packInTheirZone(int id){
    float temp[3];
    game.getItemLoc(temp, id);
    if(compareVector(temp, theirZone, 0.08))
        return true;
    else
        return false;
}


//get our position. Smooth af

void getMyPos() {
    api.getMyZRState(myState);
    copyArray(myState, myPos, 0, 3);
}
