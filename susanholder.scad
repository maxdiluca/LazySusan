//number of samples
nd=4;
//size of the samples
w=25;
h=40;



dan=360/nd;


thicknesstop=2;

brimthichnkess=2;
brimheight=10;
diametersusan=139;



difference(){
         translate([0,0,-brimheight])
            cylinder(brimheight+thicknesstop,d=brimthichnkess*2+diametersusan,$fn=200);
   
    union(){
       for(a=[0:dan:359.9]){
        rotate([0,0,a]){
           translate([-w/2,h/2+8.2,-5]){
            cube([w,h,10]);
               translate([w/2,h/2,0]){
          for (x=[-w/2+.5,w/2-.5]){
             for (y=[-h/2+.5,h/2-.5]){
                 translate([x,y,-10])
                cylinder(20,.8,.8,$fn=20);
             }
         }
     }
 }
 }
        };
        translate([0,0,-300])
         cylinder(400,d=50,$fn=200);
   
             translate([0,0,-400])
         cylinder(400,d=diametersusan,$fn=200);
  
    };

    
}