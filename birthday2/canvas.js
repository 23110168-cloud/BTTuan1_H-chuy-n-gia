var canvas = document.getElementById("canvas");
var ctx = canvas.getContext("2d");
canvas.width = window.innerWidth;
canvas.height = window.innerHeight;

function drawFlower(x, y, radius, color) {
  ctx.beginPath();
  for (let i = 0; i < 8; i++) {
    let angle = (i * Math.PI) / 4;
    let dx = x + radius * Math.cos(angle);
    let dy = y + radius * Math.sin(angle);
    ctx.moveTo(x, y);
    ctx.lineTo(dx, dy);
  }
  ctx.strokeStyle = color;
  ctx.stroke();
}

setInterval(() => {
  let x = Math.random() * canvas.width;
  let y = Math.random() * canvas.height;
  let radius = Math.random() * 20 + 10;
  drawFlower(x, y, radius, `hsl(${Math.random() * 360}, 100%, 70%)`);
}, 300);