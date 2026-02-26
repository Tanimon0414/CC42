#!/usr/bin/env bash
set -u

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
APP="$ROOT_DIR/miniRT"
DIR="$ROOT_DIR/scenes/correction_mandatory"

CASES=(
"01_basic_shapes_sphere.rt|Basic Shapes: sphere visible / no glitch"
"02_basic_shapes_plane_z0.rt|Basic Shapes: plane(z=0) visible / no glitch"
"03_basic_shapes_cylinder_y.rt|Basic Shapes: y-axis cylinder visible / no glitch"
"04_translation_two_spheres.rt|Translation: two spheres both visible"
"05_rotation_cylinder_pi2z.rt|Rotation: cylinder rotated PI/2 around z"
"06_multi_objects_intersection.rt|Multi-objects: intersection region stable"
"07_camera_axis_x.rt|Camera: x-axis setup visible"
"08_camera_axis_y.rt|Camera: y-axis setup visible"
"09_camera_axis_z.rt|Camera: z-axis setup visible"
"10_camera_random.rt|Camera: random position/direction visible"
"11_brightness_side_light_center.rt|Brightness: side light on centered sphere"
"12_brightness_side_light_translated.rt|Brightness: translated sphere lit correctly"
"13_shadow_sphere_on_plane.rt|Shadow: sphere shadow on plane"
"14_shadow_complex.rt|Shadow: complex scene shadows stable"
)

build() {
	echo "[build] make"
	if ! make -C "$ROOT_DIR" >/tmp/minirt_review_make.log 2>&1; then
		echo "[FAIL] build failed"
		sed -n '1,80p' /tmp/minirt_review_make.log
		exit 1
	fi
}

check_scene_files() {
	local row scene
	for row in "${CASES[@]}"; do
		scene="${row%%|*}"
		if [ ! -f "$DIR/$scene" ]; then
			echo "[FAIL] missing scene: $scene"
			exit 1
		fi
	done
}

review_loop() {
	local idx row scene note
	idx=1
	for row in "${CASES[@]}"; do
		scene="${row%%|*}"
		note="${row#*|}"
		echo ""
		echo "[$idx/14] $scene"
		echo "check: $note"
		echo "close window (ESC or red cross) to continue"
		read -r -p "press Enter to launch... " _
		"$APP" "$DIR/$scene"
		echo "done: $scene"
		idx=$((idx + 1))
	done
}

build
check_scene_files
review_loop

echo ""
echo "All correction-sheet mandatory visual cases done."
