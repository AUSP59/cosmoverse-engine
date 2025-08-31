
# Kubernetes deployment (hardened)
- Uses `RuntimeDefault` seccomp and `runAsNonRoot`.
- Drops all Linux capabilities and uses a read-only filesystem.
- Applies a default **deny-all** NetworkPolicy.
Edit `k8s/deployment.yaml` to set command/args for your workload.
