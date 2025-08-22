var to = nameGirl;
var gift_url = giftUrl;
var gift_image_url = giftImage || giftImageBase64;

var nametag = document.getElementById("nametag");
var present = document.getElementById("present");
var presentImage = document.getElementById("present-image");

function init() {
  var graphElem = document.querySelector('.present-box > .side.top .to');
  graphElem.setAttribute('data-before', eventName);
  document.querySelector('#card .title-card').innerHTML = `🎂 ${titleCard} 🎂`;
  document.querySelector('#card .content-card').innerHTML = `${contentCard}`;

  // Thay vì ảnh, hiển thị video khi mở hộp
  present.addEventListener("click", function(e){
    present.classList.toggle("open");
    document.getElementById('card').classList.add('card-show');
    document.getElementById('birthday-video').style.display = 'block';
    document.getElementById('birthday-video').play();
  }, false);

  nametag.innerText = to;
}

init();