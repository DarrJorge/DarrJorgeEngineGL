#!/usr/bin/env bash
set -euo pipefail

# check if python installed
if command -v python3 >/dev/null 2>&1; then
  PYTHON="python3"
elif command -v python >/dev/null 2>&1; then
  PYTHON="python"
else
  echo "Python is not installed. Please install Python to continue."
  exit 1
fi

# check args
if [[ $# -lt 1 ]]; then
  echo "Usage: ./build.sh clean|generate|build|clang_format [configuration]"
  exit 1
fi

ACTION="$1"
CONFIGURATION="${2:-}"

# keep your original path (case-sensitive on mac depending on FS)
AUTOMATION_SCRIPT="Automation/automation.py"
if [[ ! -f "$AUTOMATION_SCRIPT" ]]; then
  # fallback if you actually have "automation/automation.py"
  if [[ -f "automation/automation.py" ]]; then
    AUTOMATION_SCRIPT="automation/automation.py"
  else
    echo "Automation script not found: Automation/automation.py (or automation/automation.py)"
    exit 1
  fi
fi

if [[ -z "$CONFIGURATION" ]]; then
  "$PYTHON" "$AUTOMATION_SCRIPT" "$ACTION"
else
  "$PYTHON" "$AUTOMATION_SCRIPT" "$ACTION" --configuration "$CONFIGURATION"
fi