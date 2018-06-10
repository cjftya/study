class Circle {
  constructor(x, y, s) {
    this.pos = new Vector2d();
    this.pos.x = x;
    this.pos.y = y;

    this.vel = new Vector2d();
    this.size = s;
    this.radius = s / 2;
    this.angle = 0;
  }

  update() {
  }

  draw() {
    stroke(0);
    fill(255, 0, 0);
    ellipse(this.pos.x, this.pos.y, this.radius, this.radius);
  }
};
