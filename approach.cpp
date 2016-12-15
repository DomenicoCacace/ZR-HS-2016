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

void approachPack(){
    if(!compareVector(myPos, virtualTarget, 0.005)){
        if ((dist(myPos, virtualTarget)>dist(myPos, actualTarget)) && (dist(myPos, virtualTarget)<=0.5)){
            DEBUG(("GOING AROUND"));
            goAround();
        }
            else{
            api.setPositionTarget(virtualTarget);
        }
    }
}


/*we go to the docking point*/

void goAround(){
    float dist[3];
    float max=-1;
    int max_num=-1;
    for(int i = 0; i<3; ++i){
        dist[i] = fabsf(myState[i]-itemState[i]);
        if (dist[i]>max){
            max = dist[i];
            max_num = i;
        }
    }
    
    float force_point[3];
    for(int i =0; i<3;++i)
        force_point[i] = itemAtt[i];
    force_point[max_num]*=-1;
    counter++;
    if (counter % 2 == 0) api.setForces(force_point);
}


/*this function let us fly around an item to avoid collision*/