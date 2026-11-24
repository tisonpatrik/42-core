#!/bin/sh
# Create the Inception VM in the libvirt user session (no root needed).
#   home:   vm/create.sh
#   school: VM_DIR=/sgoinfre/ptison/vms vm/create.sh
set -eu

VM_NAME=${VM_NAME:-inception}
VM_DIR=${VM_DIR:-$HOME/vms}
IMAGE_URL=https://cloud.debian.org/images/cloud/trixie/latest/debian-13-generic-amd64.qcow2
BASE=$VM_DIR/$(basename "$IMAGE_URL")
DISK=$VM_DIR/$VM_NAME.qcow2
USER_DATA=$(dirname "$0")/user-data

if [ -e "$DISK" ]; then
	echo "$DISK already exists. To start over:" >&2
	echo "  virsh -c qemu:///session undefine $VM_NAME; rm $DISK" >&2
	exit 1
fi

mkdir -p "$VM_DIR"
chmod 700 "$VM_DIR"

if [ ! -f "$BASE" ]; then
	curl -fL --progress-bar -o "$BASE.part" "$IMAGE_URL"
	mv "$BASE.part" "$BASE"
fi

# Thin overlay on top of the pristine image; grows only as data is written.
qemu-img create -q -f qcow2 -b "$BASE" -F qcow2 "$DISK" 20G

virt-install \
	--connect qemu:///session \
	--name "$VM_NAME" \
	--osinfo debian11 \
	--memory 4096 \
	--vcpus 4 \
	--import \
	--disk "path=$DISK,bus=virtio" \
	--network user,model=virtio \
	--graphics spice \
	--video virtio \
	--cloud-init "user-data=$USER_DATA" \
	--noautoconsole \
	--wait 30

echo "VM '$VM_NAME' is ready: open it in virt-manager (QEMU/KVM User session)."
