videoManager = jvgslua.VideoManager_getInstance()
videoManager:setVideoMode(jvgslua.Vector2D(600, 400), "jvgs")

levelManager = jvgslua.LevelManager_getInstance()
levelManager:queueLevel("resources/level.xml")

levelManager:run()
