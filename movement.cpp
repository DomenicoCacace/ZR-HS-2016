void rotateToPoint(float target[3]){
    float temp[3];
    getMyPos();
    mathVecSubtract(temp, target, myPos, 3);
    mathVecNormalize(temp, 3);
    api.setAttitudeTarget(temp);
}

/*rotates to a point*/


void setZonePoint(){
    game.getItemLoc(actualTarget, targetNumber);
    ourZonePos[0] = actualTarget[0];
    ourZonePos[1] = actualTarget[1];
    if(actualTarget[2]>0.1)
        ourZonePos[2] = actualTarget[2] - 0.1;
    else
        ourZonePos[2] = actualTarget[2] + 0.1;
}