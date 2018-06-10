class Vector2d {
  constructor() {
    this.x = 0;
    this.y = 0;
  }
};

Vector2d.prototype.neg = function() {
  this.x *= -1;
  this.y *= -1
};

Vector2d.prototype.dot = function() {
  return this.x * this.x + this.y * this.y;
};

Vector2d.prototype.dir = function() {
  var s = Math.sqrt(this.x * this.x + this.y * this.y);
  return new Vector2d(this.x / s, this.y / s);
};

Vector2d.prototype.length = function() {
  return Math.sqrt(this.x * this.x + this.y * this.y);
};
