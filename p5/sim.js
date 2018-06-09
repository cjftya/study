var x = 100;

function setup() {
  createCanvas(500, 500);
}


function draw() {
  background(0,0,0);
   
  if(mouseIsPressed) {
    fill(255,0,0);
  } else {
    fill(0,255,0);
  }
  ellipse(100,x,50,50);

  x -= 1;
}
