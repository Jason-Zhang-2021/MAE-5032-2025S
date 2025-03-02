#!/bin/bash

# Configuration
MAX_BACKUPS=5  # Keep only the latest 5 backups

# Check if a source directory is provided as an argument
if [ -n "$1" ]; then
    SOURCE_DIR="$1"
else
    SOURCE_DIR="$HOME/mae5032_lab"  # Default directory
fi

BACKUP_DIR="$HOME/mae5032_backup"

# Ensure the source directory exists
if [ ! -d "$SOURCE_DIR" ]; then
    echo "Error: Source directory '$SOURCE_DIR' does not exist!"
    exit 1
fi

mkdir -p "$BACKUP_DIR"

# Create a timestamped backup file
BACKUP_FILE="$BACKUP_DIR/backup_$(date +%Y%m%d_%H%M%S).tar.gz"

echo "Creating backup for: $SOURCE_DIR"
tar -czf "$BACKUP_FILE" -C "$SOURCE_DIR" .

echo "Backup saved as: $BACKUP_FILE"

# Remove old backups if more than MAX_BACKUPS exist
BACKUP_COUNT=$(ls -1 "$BACKUP_DIR"/backup_*.tar.gz 2>/dev/null | wc -l)

if (( BACKUP_COUNT > MAX_BACKUPS )); then
    echo "Removing old backups..."
    ls -1t "$BACKUP_DIR"/backup_*.tar.gz | tail -n +$((MAX_BACKUPS+1)) | xargs rm -f
    echo "Old backups cleaned up."
fi

echo "Backup process completed!"

# EOF
