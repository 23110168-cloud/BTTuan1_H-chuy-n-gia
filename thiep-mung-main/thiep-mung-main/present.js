
// Cần hỗ trợ hãy liên hệ: 
// Mr-Nam http://facebook.com/nam.nodemy
// Các bạn muốn học lập trình thì tham gia Nhóm zalo tự học lập trình nhé: https://zalo.me/g/yhdkef092

var to = nameGirl;
var gift_url = giftUrl;
var gift_image_url = giftImage || giftImageBase64;

var nametag = document.getElementById("nametag");
var present = document.getElementById("present");
var presentImage = document.getElementById("present-image");

function init() {
  var graphElem = document.querySelector('.present-box > .side.top .to');
  graphElem.setAttribute('data-before', eventName);
  document.querySelector('#card .title-card').innerHTML = `💘${titleCard}💘`;
  document.querySelector('#card .content-card').innerHTML = `${contentCard}`;
  document.querySelector('#card .honey').setAttribute('src', `${giftImage}`);

  var _giftLink, 
      _giftImg;
  
  if (gift_url) {
    _giftLink = document.createElement("a");
    _giftLink.href = gift_url;
    _giftLink.target = "_blank";
    presentImage.appendChild(_giftLink);
  }
  
  if (giftVideo) {
    const videoElem = document.createElement("video");
    videoElem.src = giftVideo;
    videoElem.controls = true;
    videoElem.autoplay = true;
    videoElem.loop = true;
    videoElem.style.maxWidth = "100%";
    videoElem.style.borderRadius = "12px";

    if (_giftLink) {
      _giftLink.appendChild(videoElem);
    } else {
      presentImage.appendChild(videoElem);
    }
  }

    
  present.addEventListener("click", function(e){
    present.classList.toggle("open");
    document.getElementById('card').classList.add('card-show');
  }, false);
  
  
  
  nametag.innerText = to;
}

init();

