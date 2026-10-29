FROM debian:bookworm-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential cmake ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
COPY . /workspace
CMD ["./verify.sh"]
