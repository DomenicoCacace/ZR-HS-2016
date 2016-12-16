void rotateToPoint(float target[3]){
    float temp[3];
    getMyPos();
    mathVecSubtract(temp, target, myPos, 3);
    mathVecNormalize(temp, 3);
    api.setAttitudeTarget(temp);
}

/*rotates to a point*/

void moveTo(float* target){
    float between[3];
    for(int i =0; i<3; ++i){
        between[i] = target[i] - myState[i];
    }
    
    float curDis = dist(myState, target);
    
    if (curDis >= 0.05){ // distance on what it really shouldnt apply forces
        if (counter % 4 == 0) api.setForces(between); //frequency of applying forces. frequency is more when number is less 
        counter++;
    }
    api.setPositionTarget(target);
}


void goAround(int targetNumber){
    game.getItemZRState(itemState, targetNumber);
    float itemAtt[3], dist, b[3], c[3], forcePoint[3];
    float max=-1;
    int max_num=-1;
    for(int i =0; i<3; ++i)
        itemAtt[i] = itemState[6+i];
    for(int i = 0; i<3; ++i){
        dist = fabsf(myState[i]-itemState[i]);
        if (dist>max){
            max = dist;
            max_num = i;
        }
    }
    for(int i =0; i<3;++i)
        forcePoint[i] = itemAtt[i];
    forcePoint[max_num]*=-1;
    mathVecAdd(c, forcePoint, itemAtt, 3);
    mathVecNormalize(c, 3);
    for(int i = 0; i < 3; ++ i)
        c[i]/=4;
    mathVecAdd(b, virtualTarget, c, 3);
    moveTo(b);
}

void approachPack(){
    float x[3];
    float a, b, c;
    for(int i = 0; i < 3; ++i)
        x[i] = itemAtt[i] + actualTarget[i];
    if(!compareVector(myPos, virtualTarget, 0.005)){
        a = dist(myPos, virtualTarget);
        b = dist(x, virtualTarget);
        c = dist(myPos, x);
        if(a*a + b*b < c*c)
            goAround(targetNumber);
        else
            moveTo(virtualTarget);
    }
}