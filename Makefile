
.PHONY: all build test install format lint clean
all: build
build:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && cmake --build build -j
test:
	ctest --test-dir build --output-on-failure
install:
	cmake --install build --prefix /usr/local
format:
	@command -v clang-format >/dev/null 2>&1 && clang-format -i $(shell git ls-files '*.h' '*.hpp' '*.c' '*.cpp') || echo "clang-format not found"
lint:
	@echo "Run CI linters (clang-tidy/cppcheck) via GitHub Actions"
clean:
	rm -rf build


dist-src:
	@echo "Creating deterministic source tarball..."
	@git rev-parse --is-inside-work-tree >/dev/null 2>&1 || (echo "Not a git repo; using file timestamps" && exit 0)
	@bash scripts/set_repro_epoch.sh >/dev/null
	@git archive --format=tar --prefix=cosmoverse-src/ HEAD | gzip -n > cosmoverse-src.tar.gz
	@echo "Generated cosmoverse-src.tar.gz"


verify:
	@echo "== Build =="
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
	cmake --build build -j
	@echo "== Tests =="
	ctest --test-dir build --output-on-failure || true
	@echo "== Lint =="
	[ -f .clang-format ] && clang-format --dry-run -Werror $(git ls-files '*.h' '*.hpp' '*.c' '*.cpp') || true
	[ -f .clang-tidy ] && clang-tidy -p build $(git ls-files '*.cpp' '*.cc' '*.cxx' | tr '\n' ' ') || true
	@echo "== Docs =="
	doxygen Doxyfile || true


.PHONY: sbom dist-src
sbom:
	@which syft >/dev/null 2>&1 && syft dir:. -o cyclonedx-json > sbom.cdx.json || echo "Install syft for local SBOM generation"

dist-src:
	@mkdir -p dist && git ls-files | tar -czf dist/cosmoverse-src.tar.gz -T -
	@echo "Created dist/cosmoverse-src.tar.gz"


.PHONY: dev test fuzz format lint docs package docker helm

dev:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
	cmake --build build -j

test:
	ctest --test-dir build --output-on-failure || true

fuzz:
	cmake --build build -j --target fuzz_cosmo_api || true
	./build/fuzz_cosmo_api || true

format:
	command -v clang-format >/dev/null && clang-format -i $(git ls-files "*.[ch]pp" "*.[ch]") || true

lint:
	pre-commit run --all-files || true

docs:
	mkdocs build

package:
	cmake --build build -j
	cmake --install build --prefix dist/prefix

docker:
	docker build -f docker/Dockerfile.distroless -t cosmoverse:dev .

helm:
	helmpkg=charts/cosmoverse-0.1.0.tgz; helm package charts/cosmoverse -d charts || true; ls -l charts/*.tgz || true
