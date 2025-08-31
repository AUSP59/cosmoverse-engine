
{
  description = "COSMOVERSE ENGINE dev shell";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-24.05";
  outputs = { self, nixpkgs }: let
    pkgs = import nixpkgs { system = "x86_64-linux"; };
  in {
    devShells.x86_64-linux.default = pkgs.mkShell {
      packages = with pkgs; [ cmake ninja gcc clang clang-tools ccache lcov pkg-config doxygen python3 ];
      shellHook = ''
        echo "COSMOVERSE dev shell ready"
      '';
    };
  };
}
