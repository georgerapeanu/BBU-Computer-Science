extends Node3D

var countToWait = 4

# Called when the node enters the scene tree for the first time.
func _ready():
	$sparks.emitting = true
	$flash.emitting = true
	$fire.emitting = true
	$smoke.emitting = true
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	
	
func destory():
	queue_free()

func _on_animation_finished():
	countToWait -= 1
	if countToWait == 0:
		destory()

@rpc("any_peer", "call_local", "reliable")
func set_initial_global_position(_global_position: Vector3):
	global_position = _global_position
