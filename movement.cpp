void rotateToPoint(float target[3]){
    float temp[3];
    getMyPos();
    mathVecSubtract(temp, target, myPos, 3);
    mathVecNormalize(temp, 3);
    api.setAttitudeTarget(temp);
}

/*rotates to a point*/
