import os
from pathlib import Path
from subprocess import run

# Folder structure
RAW_DIR = "raw"    # your editable files
DATA_DIR = "data"  # PlatformIO will upload this

# Ensure data folder exists
Path(DATA_DIR).mkdir(exist_ok=True)

# Walk through raw folder
for root, dirs, files in os.walk(RAW_DIR):
    for f in files:
        src_path = Path(root) / f

        # Compute relative path from RAW_DIR
        rel_path = src_path.relative_to(RAW_DIR)
        dest_path = Path(DATA_DIR) / rel_path

        # Ensure destination folder exists
        dest_path.parent.mkdir(parents=True, exist_ok=True)

        # Minify based on file type
        if f.endswith(".html"):
            run([
                "html-minifier-terser",
                "--collapse-whitespace",
                "--remove-comments",
                "--remove-optional-tags",
                "--minify-js", "true",
                "--minify-css", "true",
                str(src_path),
                "-o", str(dest_path)
            ])
        elif f.endswith(".css"):
            run([
                "cleancss",
                "-o", str(dest_path),
                str(src_path)
            ])
        elif f.endswith(".js"):
            run([
                "terser",
                "-c",   # compress
                "-m",   # mangle
                "-o", str(dest_path),
                str(src_path)
            ])
        else:
            # Copy other files as-is (images, icons)
            from shutil import copy2
            copy2(src_path, dest_path)

print("✅ Minification complete: raw -> data")
