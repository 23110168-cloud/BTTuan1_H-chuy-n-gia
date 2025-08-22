// URL ảnh nền Pexels
const bgImageUrl = 'https://images.pexels.com/photos/1374892/pexels-photo-1374892.jpeg?auto=compress&cs=tinysrgb&w=1260&h=750&dpr=2';
let bgImg = new Image();
bgImg.crossOrigin = 'anonymous';
bgImg.src = bgImageUrl;

(function() {
  const canvas = document.getElementById('canvas');
  const ctx = canvas.getContext('2d');
  let particles = [];
  const maxParticles = 200;

  // Resize canvas cho full màn hình
  function scaleCanvas() {
    const w = Math.max(document.documentElement.clientWidth, window.innerWidth);
    const h = Math.max(document.documentElement.clientHeight, window.innerHeight);
    canvas.width = w;
    canvas.height = h;
  }

  // Tạo một hạt lửa mới
  function createParticle() {
    return {
      x: Math.random() * canvas.width,
      y: canvas.height + 10,
      size: Math.random() * 30 + 20,
      speedY: Math.random() * 1 + 0.5,
      alpha: 1,
      fade: Math.random() * 0.02 + 0.005
    };
  }

  // Vẽ nền + cập nhật và vẽ các hạt lửa
  function drawFire() {
    scaleCanvas();

    // 1) Vẽ ảnh nền
    if (bgImg.complete) {
      ctx.drawImage(bgImg, 0, 0, canvas.width, canvas.height);
    } else {
      ctx.clearRect(0, 0, canvas.width, canvas.height);
      bgImg.onload = drawFire;
      return;
    }

    // 2) Thêm hạt mới nếu chưa đủ
    if (particles.length < maxParticles) {
      particles.push(createParticle());
    }

    // 3) Cập nhật và vẽ từng hạt
    for (let i = particles.length - 1; i >= 0; i--) {
      const p = particles[i];
      p.y -= p.speedY * 2;
      p.alpha -= p.fade;

      // Xóa hạt nếu đã tắt hẳn
      if (p.alpha <= 0) {
        particles.splice(i, 1);
        continue;
      }

      // Tạo gradient từ vàng sang đỏ rồi trong suốt
      const grad = ctx.createRadialGradient(p.x, p.y, 0, p.x, p.y, p.size);
      grad.addColorStop(0, `rgba(255,255,0,${p.alpha})`);
      grad.addColorStop(0.5, `rgba(255,0,0,${p.alpha * 0.6})`);
      grad.addColorStop(1, 'rgba(0,0,0,0)');

      ctx.fillStyle = grad;
      ctx.beginPath();
      ctx.arc(p.x, p.y, p.size, 0, Math.PI * 2);
      ctx.fill();
    }

    // Lặp lại
    requestAnimationFrame(drawFire);
  }

  // Khởi chạy
  drawFire();
  window.onresize = drawFire;
})();

body.addEventListener("click", function(ev){
  drawFlowers();
  playMusic(); // gọi play nhạc sau khi click
});
