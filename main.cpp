float   myState[12];            //status of the sphere
float   myPos[3];               //our position
float   theirPos[3];
float   itemState[12];          //state of the item
float   itemAtt[3];             //attitude of the item
float   pointAtt[3];            //point attitude
float   second[3];              //point to place SPS
float   third[3];
float   dropPos[3];
float   dropZone[3];
float   temp[3];

float   virtualTarget[3];       //we calculate and fly to this point
float   actualTarget[3];        //actual location of an item
float   distFromTarget;         //distance from our target
int     targetNumber;           //ID of the item
float   distMin;                //minimum distance of docking
float   distMax;                //maximum distance of docking

float   ranking[4];             //vector that is used to calculate which item is the worthiest

float   ourZone[3];             //our assembly zone
float   theirZone[3];           //they assembly zone

char    index;                  //switch index
bool    calculated;             //check if the virtualPoint is calculated
int     counter;                //counter used to fly around objects
int     packsInZone;

void init(){
    packsInZone = 0;
    getMyPos();
    getTheirPos();
    index = 's';                //index starts here
    game.dropSPS();             //we drop the first SPS at our starting point
    calculated = false;
    if(ourColor() == 'B'){
        assign(second, 0.0, 0.15, 0.60);
        assign(third, 0.60, 0.0, 0.60);
    }
    else{
        assign(second, 0.0, 0.0, -0.60);
        assign(third, -0.60, 0.0, -0.60);
    }
    setDist();
}

void loop(){
    getMyPos();                            //we get our position because we always need that information
    packsInZone = 0;
    for(int i = 0; i < 4; i++){
        game.getItemLoc(temp, i);
        if(compareVector(ourZone, temp, 0.05))
            packsInZone++;
        }
    if((game.getCurrentTime() >= 140 || packsInZone == 2) && index == 'p' )
        index = 'f';
    switch(index){
        /*we call worthyPack to see what is the worthiest pack to pick up. If we didn't place the SPS we will go to case F and place it, 
        otherwise we will go for packs. we calculate here the virtual point or we would follow the pack if it starts moving*/
        case 's':
            if(!compareVector(myPos, second, 0.10))
                api.setPositionTarget(second);
            else{
                game.dropSPS();
                index = '3';
            }
            break;
        /*we calculate the position of the second SPS based on the position of the first worthyPack we find*/
        case '3':
            if(!compareVector(myPos, third, 0.10))
                api.setPositionTarget(third);
            else{
                game.dropSPS();
                zoneInfo();
                index = 'p';
            }
            break;
        /* */
        case 'p':
            worthyPack();
            if(!calculated)
                calcPoint();
            else{
                approachPack();
                api.setAttitudeTarget(pointAtt);
                DEBUG(("%f", dist(myPos, actualTarget)));
                if(dist(myPos, actualTarget)<=distMax && dist(myPos, actualTarget) >= distMin && game.isFacingCorrectItemSide(targetNumber)){
                    if(game.dockItem(targetNumber) && game.hasItem(targetNumber) == 1){
                        game.dropSPS();
                        assign(dropPos, myPos[0], myPos[1], myPos[2]);
                        index = 'z';
                    }
                }
            }
            break;
        /*we calculate the approach point. if the pack is moving we return to worthyPack, otherwise we go and dock the item. The first
        dock will place the last SPS and get the ZoneInfo*/
        case 'z':
            rotateToPoint(ourZone);
                api.setPositionTarget(ourZone);
            if((dist(dropPos, ourZone) < 0.2))
                assign(dropZone, ourZone[0], ourZone[1], ourZone[2] - 0.2);
            if(packInZone()){
                game.dropItem();
                index = 'p';
                calculated = false;
            }
            break;
        /*we drop the item in the zone. the first time we drop the item and calculate an universal dropping point*/
        case 'f':
            api.setPositionTarget(ourZone);
            DEBUG(("VUÒ FA' CODICE E CODICE? PO PO PO PO PO PO"));
        break;
    }
}
