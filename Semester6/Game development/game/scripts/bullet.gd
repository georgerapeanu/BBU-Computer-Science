extends RigidBody3D

@export var IMPULSE_STRENGTH = 10
@onready var explosionScene = load("res://scenes/explosion.tscn")
@export var shooter_id: int
# Called when the node enters the scene tree for the first time.
func _ready():
	$Timer.connect("timeout", get_hit)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta):
	pass
	


@rpc("any_peer", "call_local", "reliable")
func get_hit():
	summon_explosion(global_position)
	queue_free()


func summon_explosion(_global_position):
	var explosion = explosionScene.instantiate()
	get_node("/root/ui/MultiplayerSpawner").add_child(explosion, true)
	explosion.global_position = _global_position
	



func _on_body_entered(body):
	if body == get_node("."):
		return
	if body.get("is_tank") == true && shooter_id != body.name.to_int():
		get_node("/root/ui/MultiplayerSpawner/" + str(shooter_id)).increment_score.rpc_id(shooter_id)
	if body.has_method("get_hit"): # Check if there is one first
		body.get_hit.rpc()
		get_hit.rpc()

