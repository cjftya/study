let circle;

function setup() {
  createCanvas(500, 500);

  circle = new Circle(100, 100, 50);
}


function draw() {
  background(0, 0, 0);
  circle.update();
  circle.draw();
}
