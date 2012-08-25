<?php
if($_GET['file'] == NULL || $_GET['type'] == NULL) {
die("You must input a file to play and its type (e. g. video/ogg)");
} else {
?>
<!DOCTYPE html>
<html>
<head>
<link href="http://vjs.zencdn.net/c/video-js.css" rel="stylesheet">
<script src="http://vjs.zencdn.net/c/video.js"></script>
<title><?php echo $_GET['file']; ?> - powered by Video.js</title>
</head>
<body>
<h1>Watch <?php echo $_GET['file']; ?> below:</h1><br />
<video id="play" class="video-js vjs-default-skin" controls width="640" height="480" poster="http://video-js.zencoder.com/oceans-clip.jpg" preload="auto" data-setup="{}">
<source type="<?php echo $_GET['type']; ?>" src="<?php echo $_GET['file']; ?>">
</video><br />
Powered by <a href="http://videojs.com">Video.js</a>
</body>
</html>
<?php
}
?>
