/*Creates a 1d texture wit equally-spaced ridges
Massimiliano Di Luca
m.diluca@bham.ac.uk
September 10, 2020*/

//measures in millimiters

gmin=120;
gstep=120;
gmax=500;


repetitions=3;




ridge=.12;

w=25;
l=40;
hbase=1.8;
hridges=.3;
        
        
        
        
for (n=[1:1:repetitions]){
    for (g=[gmin:gstep:gmax]){
        translate([n*30,(g-gmin)/gstep*30,0])
        rotate([0,90,180])
texture(g/1000);
    }
}

//groove=1.2;


        
        
        module texture(groove){

//center the texture elements on the base
texturestart=((l-ridge)%(groove+ridge))/2;

 
   
difference(){
translate([0,0,hbase]){
union(){
    translate([-l/2,-w/2,-hbase])
    cube([l,w,hbase]);

for (p=[texturestart:(groove+ridge):l-ridge]){
    translate([p-l/2,-w/2,-.1])
        cube([ridge, w, (hridges +.1)]);
     
}
}
};
  
rotate([180,0,180])
translate([0,-w/2+2,-.1])
linear_extrude(11){
  text(text = str(groove*1000,"µm"), font = "Arial", size = 6, halign =  "center");
    }

rotate([180,0,180])
translate([0,-3,-.1])
linear_extrude(11){
  text(text = str(ridge*1000,"µm"), font = "Arial", size = 6, halign =  "center");
    }
    
    rotate([180,0,180])
translate([0,w/2-7,-.1])
linear_extrude(11){
  text(text = str(hridges*1000,"µm"), font = "Arial", size = 6, halign =  "center");
    }

}
}