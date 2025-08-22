var to = nameGirl;
var gift_url = giftUrl;
var gift_image_url = giftImage || giftImageBase64;

var nametag = document.getElementById("nametag");
var present = document.getElementById("present");
var presentImage = document.getElementById("present-image");

function init() {
  var graphElem = document.querySelector('.present-box > .side.top .to');
  graphElem.setAttribute('data-before', eventName);
  document.querySelector('#card .title-card').innerHTML = `💝 ${titleCard} 💝`;
  document.querySelector('#card .content-card').innerHTML = `${contentCard}`;

  nametag.innerText = to;

  present.addEventListener("click", function () {
    present.classList.toggle("open");
    document.getElementById('card').classList.add('card-show');
  }, false);
}

window.onload = init;