# wolf3d
Inspired by the famous eponymous 90s game that was the first First Person Shooter, this project tackles the technique of ray-casting.

#
![](regularMode.gif) ![](secretMode.gif)
#

### Usage
  ./wolf3d <map_file>
	<map_file> size must be at least 3x3
  
### Basic Control
  - KEYS:  
	[W,S]/[Arrow Key - Up,Down] - Move Forward/Backward  
	[A,D]/[Arrow Key - Left,Right] - Rotate Left/Right  
	[SHIFT] - Run/Walk  
	[ESC] - Exit  
	[SPACE] - Open Hidden Door  

		- SECRET MODE:  
		(Press [6] during intro screen)  
  
		[R] - Pull In/Out Gun  
		[Space] - Shoot  
		[Q] - Reload  
 
 
## Goals
- [x] Player can choose the size and the shape of the labyrinth, but the map has to be a file outside of sources.
- [x] The management of game window must remain smooth: passing over of another window, minimization, etc.
- [x] Pressing ESC must close the window and quit the program cleanly.
- [x] Clicking on the red cross on the window's fram must close the window and quit the program cleanly.
- [x] The arrows on the keyboard must allow player to move in real time in the maze, like in the original game.
- [x] Display different wall textures that vary depending on which compass point the wall is facing.
  
## Bonus
- [x] Wall collisions
- [x] Floor and/or ceiling texture
- [x] Secret doors
- [x] Sounds and music
- [x] Weapon and be fired
- [x] Bullet management
