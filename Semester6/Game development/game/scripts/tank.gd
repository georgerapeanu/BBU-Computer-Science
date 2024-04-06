extends CharacterBody3D


@export var SPEED = 5.0
@export var TURN_SPEED = 1.0

# Get the gravity from the project settings to be synced with RigidBody nodes.
var canShoot = true
@onready var bulletScene = load("res://scenes/bullet.tscn")
@onready var bulletSpawn = $bulletSpawn
@onready var timer = $bulletTimer as Timer
var gravity = ProjectSettings.get_setting("physics/3d/default_gravity")
var score = 0
var is_tank = true

func _enter_tree():
	set_multiplayer_authority(name.to_int())

func _ready():
	timer.connect("timeout", _on_shoot_timer)
	if is_multiplayer_authority():
		$SpringArm3D/Camera3D.current = true

func _on_shoot_timer():
	canShoot = true

# TODO fix spawning bullets in walls
func shoot():
	canShoot = false
	summon_bullet.rpc_id(1, bulletSpawn.global_position, basis.z, multiplayer.get_unique_id())
	timer.start()

@rpc("any_peer", "call_local")
func summon_bullet(_global_position, impulse, id):
	var bullet = bulletScene.instantiate()
	bullet.global_position = _global_position
	bullet.apply_central_impulse(impulse * bullet.IMPULSE_STRENGTH)
	bullet.shooter_id = id
	get_node("/root/ui/MultiplayerSpawner").add_child(bullet, true)
	

@rpc("any_peer", "call_local", "reliable")
func get_hit():
	respawn()

func respawn():
	var spawnpoints = get_node("/root/ui/spawnpoints").get_children()
	var spawnpoint = spawnpoints[randi() % spawnpoints.size()]
	global_position = spawnpoint.global_position

func _physics_process(delta):
	# Get the input direction and handle the movement/deceleration.
	# As good practice, you should replace UI actions with custom gameplay actions.
	if is_multiplayer_authority():
		if not is_on_floor():
			velocity.y -= gravity * delta
		var input_dir = Input.get_vector("ui_right", "ui_left", "ui_down", "ui_up")
		var turn = input_dir.x / abs(input_dir.x) if input_dir.x != 0 else 0
		rotation.y += turn * TURN_SPEED * delta
		
		if Input.is_action_just_pressed("ui_select"):
			if canShoot:
				shoot()
		
		var direction = (transform.basis * Vector3(0, 0, input_dir.y)).normalized()
		if direction:
			velocity.x = direction.x * SPEED
			velocity.z = direction.z * SPEED
		else:
			velocity.x = move_toward(velocity.x, 0, SPEED)
			velocity.z = move_toward(velocity.z, 0, SPEED)

	move_and_slide()

@rpc("call_local", "any_peer")
func increment_score():
	score += 1
	get_node("/root/ui/score").set_text("score: " + str(score))

@rpc("any_peer", "call_local", "reliable")
func set_initial_global_position(_global_position: Vector3):
	global_position = _global_position
