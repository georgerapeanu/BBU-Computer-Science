extends Node3D


var peer = ENetMultiplayerPeer.new()
@export var play_scene: PackedScene
@onready var spawnpoints = $spawnpoints.get_children()

func _on_host_pressed():
	peer.create_server(27015)
	multiplayer.multiplayer_peer = peer 
	multiplayer.peer_connected.connect(_add_player)
	_add_player()
	$host.hide()
	$join.hide()
	$score.show()

func _add_player(id = 1):
	var player = play_scene.instantiate()
	player.name = str(id)
	var spawnpoint = spawnpoints[randi() % spawnpoints.size()]
	player.scale = Vector3(0.5, 0.5, 0.5)
	$MultiplayerSpawner.add_child(player)
	player.set_initial_global_position.rpc(spawnpoint.global_position)

func _on_join_pressed():
	peer.create_client("localhost", 27015)
	multiplayer.multiplayer_peer = peer
	$host.hide()
	$join.hide()
	$score.show()
