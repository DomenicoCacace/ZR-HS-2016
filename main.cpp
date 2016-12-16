float   myState[12];            //status of the sphere
float   myPos[3];               //our position
float   itemState[12];          //state of the item
float   itemAtt[3];             //attitude of the item
float   pointAtt[3];            //point attitude
float   sps[3];
float   zoneData[4];

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
int     packsInZone;            //number of packs into our zone
bool    first;

void init(){
    getMyPos();
    index = 's';                //index starts here
    game.dropSPS();             //we drop the first SPS at our starting point
    calculated = false;
    if(myPos[1]>0){
        assign(sps, -0.40, 0.40, 0.0);
    }
    else{
        assign(sps, 0.40, -0.40, 0.0);
    }
    first = true;
    setDist();
}

void loop(){
    getMyPos();                            //we get our position because we always need that information
    packsInZone = 0;
    for(int i = 0; i < 4; i++){
        if(game.itemInZone(i))              //count num of packs in our zone
            packsInZone++;
    }
    
    if((game.getCurrentTime() >= 155 || packsInZone == 2) && index == 'p' ) //if time is low or we have 2 packs we go def
        index = 'f'; 
        
    if(packIsMoving(targetNumber) &&  game.getNumSPSHeld() == 0 && index != 'z')    //if we hit a pack
        index = 'p';
        
    if(game.hasItem(targetNumber) == 2 || (packIsMoving(targetNumber) && index != 's'))
        index = 'p';
        
        switch(index){
        /*we call worthyPack to see what is the worthiest pack to pick up. If we didn't place the SPS we will go to case F and place it, 
        otherwise we will go for packs. we calculate here the virtual point or we would follow the pack if it starts moving*/
        case 's':
            if(!compareVector(myPos, sps, 0.10))
                moveTo(sps);
            else{
                game.dropSPS();
                index = 'p';
            }
            break;
        /*we calculate the position of the second SPS based on the position of the first worthyPack we find*/
        case 'p':
            DEBUG(("WORTHY PACK"));
            worthyPack();
            calcPoint();
            index = 'm';
            break;
        case 'm':
            DEBUG(("GETTING PACK %d", targetNumber));
            approachPack();
            api.setAttitudeTarget(pointAtt);
            DEBUG(("DIST FROM TARGET: %f", dist(myPos, actualTarget)));
            if(dist(myPos, actualTarget)<=distMax && dist(myPos, actualTarget) >= distMin && game.isFacingCorrectItemSide(targetNumber) && rightSpeed()){
                if(game.dockItem(targetNumber) && game.hasItem(targetNumber) == 1){
                    if(first){
                        game.dropSPS();
                        zoneInfo();
                        first = false;
                    }
                    index = 'z';
                }
            }
            break;
        /*we calculate the approach point. if the pack is moving we return to worthyPack, otherwise we go and dock the item. The first
        dock will place the last SPS and get the ZoneInfo*/
        case 'z':
            DEBUG(("GOING TO ZONE"));
            rotateToPoint(ourZone);
            moveTo(ourZone);
            if(packInZone(targetNumber)){
                game.dropItem();
                index = 'p';
                calculated = false;
            }
            break;
        /*we drop the item in the zone. the first time we drop the item and calculate an universal dropping point*/
        case 'f':
            moveTo(ourZone);
            break;
    }
}