var cv = require('opencv');

try {
  var camera = new cv.VideoCapture(2);
  var window = new cv.NamedWindow('Video', 0)
  while(true)
  camera.read(err,im);
  window.show(im);
  /*
  setInterval(function() {
    camera.read(function(err, im) {
      if (err) throw err;
      console.log(im.size())
      if (im.size()[0] > 0 && im.size()[1] > 0){
        window.show(im);
      }
      window.blockingWaitKey(0, 50);
    });
  }, 100);
  */
} catch (e){
  console.log("Couldn't start camera:", e)
}
