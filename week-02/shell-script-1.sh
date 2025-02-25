#!/bin/bash

# Configuration
SOURCE_DIR="$HOME/Documents"   # Directory to back up
BACKUP_DIR="$HOME/backups"     # Where backups will be stored
MAX_BACKUPS=5                  # Number of backups to keep

# Ensure backup directory exists
mkdir -p "$BACKUP_DIR"

# Create a timestamped backup file
BACKUP_FILE="$BACKUP_DIR/backup_$(date +%Y%m%d_%H%M%S).tar.gz"

echo "Creating backup for: $SOURCE_DIR"
tar -czf "$BACKUP_FILE" -C "$SOURCE_DIR" .

echo "Backup saved as: $BACKUP_FILE"

# Delete old backups if more than MAX_BACKUPS exist
BACKUP_COUNT=$(ls -1 "$BACKUP_DIR"/backup_*.tar.gz | wc -l)

if (( BACKUP_COUNT > MAX_BACKUPS )); then
    echo "Removing old backups..."
    ls -1t "$BACKUP_DIR"/backup_*.tar.gz | tail -n +$((MAX_BACKUPS+1)) | xargs rm -f
    echo "Old backups cleaned up."
fi

echo "Backup process completed!"
