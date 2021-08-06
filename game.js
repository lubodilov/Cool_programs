/**let speed = 2;
let pos = {
    x: 0, 
    y: 0
};
 
let wall = {
    pos: {
        x: 400,
        y: 300,
    },
    r: 250
};
let norm ={
    pos: {
        x: 0,
        y: 0,
    }
} 
let k2 = {
    pos: {
        x: 0,
        y: 0,
    },
    vel:{
        x: 0,
        y: 0,
    },
    r: 30
};
function vecAdd(v, u) {
    return {
        x: v.x + u.x, 
        y: v.y + u.y
    };
}
 
function vecSub(v, u) {
    return {
        x: v.x - u.x,
        y: v.y - u.y
    };
}
 
function vecMul(v, a) {
    return {
        x: v.x * a,
        y: v.y * a
    };
}
 
function vecDiv(v, a) {
    if (a == 0) return {x: 0, y: 0};
    return {
        x: v.x / a,
        y: v.y / a
    };
}
 
function vecLen(v) {
    return Math.sqrt(v.x * v.x + v.y * v.y);
}
 
function vecUnit(v) {
    return vecDiv(v, vecLen(v))
}
 
function collidingCirclePoint(k, v) {
    return vecLen(vecSub(k.pos, v)) < k.r;
}
 
function collidingCircleCircle(k1, k2) {
    return vecLen(vecSub(k1.pos, k2.pos)) < k1.r + k2.r;
}
 
function collidingCirclePerimeter(k1, k2) {
    let len = vecLen(vecSub(k1.pos, k2.pos));
    return len >= k2.r - k1.r && len <= k2.r + k1.r;
}
k2.pos = {x: wall.pos.x, y: wall.pos.y};
var vel = (Math.random()*2-1)*10;
var vel2 = (Math.random()*2-1)*10;
k2.vel.x = vel;
k2.vel.y = vel2;
k2.vel.x/=(vecLen(k2.vel)/5);
k2.vel.y/=(vecLen(k2.vel)/5);
function update() {
    k2.pos = vecAdd(k2.pos, k2.vel);
    norm.pos = vecAdd(vecSub(wall.pos,k2.pos), 0);
    if (collidingCirclePerimeter(k2, wall)) {
        k2.vel.x*=-1;
        k2.vel.y*=-1;
    }
}
 
function fillCircle(k) {
    context.beginPath();
    context.arc(k.pos.x, k.pos.y, k.r, 0, 2 * Math.PI);
    context.fill(); // za krug
}
 
function strokeCircle(k) {
    context.beginPath();
    context.arc(k.pos.x, k.pos.y, k.r, 0, 2 * Math.PI);
    context.stroke(); // za okrujnost
}
 
function draw() {
    strokeCircle(wall);
    fillCircle(k2);
};
 
function keydown(key) {
};
 
function mouseup() {
};
**/
let gravity = {x: 0, y: 1};
let history = 100;
let pos = {
    x: 0, 
    y: 0,
};
 
let wall = {
    pos: {
        x: 400,
        y: 300,
    },
    r: 300,
};
 
let particles = [];
let colors = ["red", "orange", "yellow", "lime", "cyan", "magenta"];
 
for (let i = 0; i < 6; i++) {
    particles[i] = {
        pos: {
            x: 400 + i * 50,
            y: 300,
        },
        vel: {
            x: 0,
            y: 0,
        },
        path: [],
        r: 15,
        color: colors[i],
    }
}
 
function vecAdd(v, u) {
    return {
        x: v.x + u.x, 
        y: v.y + u.y,
    };
}
 
function vecSub(v, u) {
    return {
        x: v.x - u.x,
        y: v.y - u.y,
    };
}
 
function vecMul(v, a) {
    return {
        x: v.x * a,
        y: v.y * a,
    };
}
 
function vecDiv(v, a) {
    if (a == 0) return {x: 0, y: 0};
    return {
        x: v.x / a,
        y: v.y / a,
    };
}
 
function vecLen(v) {
    return Math.sqrt(v.x * v.x + v.y * v.y);
}
 
function vecUnit(v) {
    return vecDiv(v, vecLen(v))
}
 
function vecDot(v, u) {
    return v.x * u.x + v.y * u.y;
}
 
function collidingCirclePoint(k, v) {
    return vecLen(vecSub(k.pos, v)) <= k.r;
}
 
function collidingCircleCircle(k1, k2) {
    return vecLen(vecSub(k1.pos, k2.pos)) <= k1.r + k2.r;
}
 
function collidingCirclePerimeter(k, p) {
    let len = vecLen(vecSub(k.pos, p.pos));
    return len >= p.r - k.r && len <= p.r + k.r;
}
 
function calcNorm(p, w) {
    return vecUnit(vecSub(w.pos, p.pos));
}
 
function reflect(ray, norm) {
    const r = vecMul(ray, -1);
    const nPrim = vecMul(norm, vecDot(r, norm));
    const l = vecSub(vecMul(nPrim, 2), r);
    return l;
}
 
function update() {
    for (man of particles) {
        man.vel = vecAdd(man.vel, gravity);
        man.pos = vecAdd(man.pos, man.vel);
        if (collidingCirclePerimeter(man, wall)) {
            man.pos = vecSub(man.pos, man.vel); // undo 2 lines above
            let norm = calcNorm(man, wall);
            man.vel = reflect(man.vel, norm);
        } else {
            for (woman of particles) {
                if (man == woman) continue;
                if (collidingCircleCircle(man, woman)) {
                    man.pos = vecSub(man.pos, man.vel); // undo 2 lines above
                    let norm = calcNorm(man, woman);
                    man.vel = reflect(man.vel, norm);
                }
            }
        }
    }
};
 
function fillCircle(k) {
    context.fillStyle = k.color;
    context.strokeStyle = k.color;
    k.path.push({x: k.pos.x, y: k.pos.y});
    if (k.path.length > history) {
        k.path.shift();
    }
    context.beginPath();
    context.moveTo(k.path[0].x, k.path[0].y);
    for (p of k.path)
        context.lineTo(p.x, p.y);
    context.stroke();
 
    context.beginPath();
    context.arc(k.pos.x, k.pos.y, k.r, 0, 2 * Math.PI);
    context.fill(); // za krug
}
 
function strokeCircle(k) {
    context.beginPath();
    context.arc(k.pos.x, k.pos.y, k.r, 0, 2 * Math.PI);
    context.stroke(); // za okrujnost
}
 
function draw() {
    context.fillStyle = "black";
    context.fillRect(0, 0, 800, 600);
 
    context.fillStyle = "white";
    context.strokeStyle = "white";
 
    strokeCircle(wall);
    for (p of particles) {
        fillCircle(p);
    }
};
 
function keydown(key) {
};
 
function mouseup() {
};
