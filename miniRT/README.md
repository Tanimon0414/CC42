# miniRT (42 mandatory)

This repository contains a full mandatory implementation of `miniRT` using MiniLibX.

## Implemented mandatory features

- Parsing of `.rt` scenes with strict identifiers:
  - `A` (ambient, unique)
  - `C` (camera, unique)
  - `L` (light, unique)
  - `sp`, `pl`, `cy` (objects)
- Robust value validation:
  - ratios in `[0.0, 1.0]`
  - colors in `[0, 255]`
  - normalized vectors for camera/plane/cylinder axis
  - positive diameters/heights
- Ray tracing objects:
  - sphere
  - plane
  - finite cylinder with both caps
- Lighting model:
  - ambient
  - diffuse
  - hard shadows
- Window/event behavior:
  - render to image + display in window
  - `ESC` closes the app cleanly
  - window close button also exits cleanly
- Error behavior:
  - on invalid configuration: prints `Error\n` + explicit message

## Notes about comments and norm

- Every function includes a short comment describing its purpose.
- All files under `include/` and `src/` pass `norminette`.

## Build

```bash
make
```

This Makefile builds MiniLibX (`minilibx-linux`) and then the project.

## Run

```bash
./miniRT scenes/minimal.rt
```

Sample scenes are provided in `scenes/`.
- `scenes/visible.rt`: quick visible confirmation scene
- `scenes/tests_valid/*.rt`: mandatory-valid regression scenes
- `scenes/tests_invalid/*`: parser/error regression scenes
- `scenes/correction_mandatory/*.rt`: scenes aligned with common evaluation-sheet mandatory checks

## Regression test

```bash
./scripts/test_scenes.sh
```

This script:
- builds the project
- runs valid scenes (expects no `Error`)
- runs invalid scenes (expects `Error`)
- prints a pass/fail summary

## Evaluation-sheet mandatory check

```bash
./scripts/check_correction_mandatory.sh
```

This script runs a mandatory-focused scene pack (`14` scenes) corresponding to:
- basic shapes
- translation / rotation
- multi-objects
- camera direction and position cases
- brightness and shadows

## Interactive visual review (with evaluator order)

```bash
./scripts/review_correction_cases.sh
```

This launches the 14 mandatory-focused scenes one by one.
Close each window (`ESC` or red cross) to move to the next case.

## Clean

```bash
make clean
make fclean
make re
```

## Scene format quick reference

Each non-empty line begins with an identifier:

- Ambient: `A ratio R,G,B`
- Camera: `C x,y,z nx,ny,nz fov`
- Light: `L x,y,z ratio R,G,B`
- Sphere: `sp x,y,z diameter R,G,B`
- Plane: `pl x,y,z nx,ny,nz R,G,B`
- Cylinder: `cy x,y,z nx,ny,nz diameter height R,G,B`

Examples are in `scenes/minimal.rt`.
