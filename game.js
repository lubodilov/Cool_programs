// Suzdavame promenlivi
let myX, myY;
 
function init() {
    // Kodut tuk se izpulnqva vednuj v nachaloto
    myX = 300;
    myY = 300;
}
function drawLine(startX, startY, endX, endY)
{
    context.beginPath();
    context.moveTo(startX, startY);
    context.lineTo(endX, endY);
    context.stroke();
}
class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
    draw() {
        context.fillRect(this.x - 5, this.y - 5, 10, 10);
    }
}
 
class Line {
    constructor(begin, end) {
        this.begin = begin;
        this.end = end;
 
        this.recalculate();
    }   
    draw() {
        drawLine(this.begin.x, this.begin.y, this.end.x, this.end.y);
    }
    recalculate() {
        if(this.begin.x == this.end.x) {
            this.begin.x += 0.1;            
        }
        this.m = (this.begin.y - this.end.y) / (this.begin.x - this.end.x);
        this.b = this.begin.y - this.begin.x * this.m;
    }
}
 
// Vrushta true ako ne e imalo problem.
function fixEdgeCases(wall, ray, intersection) {
    // Tova pravi fenercheto da sveti samo napred
    let isBetweenx = false, isBetweeny = false;
    if((ray.end.x <= ray.begin.x && ray.begin.x <= intersection.x) || (ray.end.x >= ray.begin.x && ray.begin.x >= intersection.x)) {
        isBetweenx = true;
    }
    if((ray.end.y <= ray.begin.y && ray.begin.y <= intersection.y) || (ray.end.y >= ray.begin.y && ray.begin.y >= intersection.y)) {
        isBetweeny = true;
    }
    if(isBetweeny && isBetweenx) {
        return false;
    }
 
    // Tova vnimava stenata da ne byde prava, a otsechka
    isBetweenx = false, isBetweeny = false;
    if((wall.begin.x <= intersection.x && intersection.x <= wall.end.x) || (wall.begin.x >= intersection.x && intersection.x >= wall.end.x)) {
        isBetweenx = true;
    }
    if((wall.begin.y <= intersection.y && intersection.y <= wall.end.y) || (wall.begin.y >= intersection.y && intersection.y >= wall.end.y)) {
        isBetweeny = true;
    }
    if(!isBetweeny || !isBetweenx) {
        return false;
    }
 
    return true;
}
 
function intersect(wall, ray) {
    wall.recalculate();
    ray.recalculate();
 
    let x = (wall.b - ray.b) / (ray.m - wall.m);
    let y = x * wall.m + wall.b;
 
    let answerPoint = new Point(x, y);
 
    if(fixEdgeCases(wall, ray, answerPoint)) {
        return answerPoint;        
    } else {
        return undefined;
    }
}
 
let player = new Point(0, 0);
let ray = new Line(player, new Point(1000, 1000));
let walls = [];
walls.push(new Line(new Point(0, 0), new Point(800, 0)));
walls.push(new Line(new Point(800, 600), new Point(800, 0)));
walls.push(new Line(new Point(800, 600), new Point(0, 600)));
walls.push(new Line(new Point(0, 0), new Point(0, 600)));
walls.push(new Line(new Point(100, 150), new Point(420, 69)));
walls.push(new Line(new Point(400, 200), new Point(500, 440)));
 
let intersections = [];
 
function distance(a, b) {
    return Math.sqrt(Math.pow((a.x - b.x), 2), Math.pow((a.y - b.y), 2));
}
 
function update() {
    // Kodut tuk se izpulnqva (okolo) 100 puti v sekunda
    myX = myX + (mouseX - myX) / 10;
    myY = myY + (mouseY - myY) / 10;
 
    player = new Point(myX, myY);
 
    ray.begin = new Point(myX, myY);
 
    intersections = []
 
    for(let angle = 0; angle < Math.PI * 2; angle += 0.002) {
        let intersection = undefined;
        minimumDistance = 100000000;
        let rotatedRay = new Line(player, new Point(player.x + Math.cos(angle), player.y + Math.sin(angle)));
 
        for(let i = 0; i < walls.length; i ++) {
            let currentIntersection = intersect(walls[i], rotatedRay);
            if(currentIntersection == undefined) {
                continue;
            } else {
                if(minimumDistance > distance(currentIntersection, player)) {
                    intersection = currentIntersection;
                    minimumDistance = distance(currentIntersection, player);
                }
            }
        }
        if(intersection != undefined) {
            intersections.push(intersection);
        }
    }
}
 
function draw() {
    // Tuk naprogramirai kakvo da se risuva
    player.draw();
 
    for(let i = 0; i < walls.length; i ++) {
        walls[i].draw();
    }
 
    if(intersections.length > 3) {
        context.beginPath();
        context.moveTo(intersections[0].x, intersections[0].y);
        for(let i = 1; i < intersections.length; i ++) {
            context.lineTo(intersections[i].x, intersections[i].y);
        }
        context.closePath();
        context.fill();
    }
 
    return;
    context.beginPath();
    context.arc(300, 300, 30, 0, 2 * Math.PI);
    context.fill();
    context.stroke();
}
function mouseup() {
    // Pri klik s lqv buton - pokaji koordinatite na mishkata
    console.log("Mouse clicked at", mouseX, mouseY);
}
function keyup(key) {
    // Pechatai koda na natisnatiq klavish
    console.log("Pressed", key);
}

