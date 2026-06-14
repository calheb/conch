{
  description = "A simple, extensible, community focused and customizable UNIX shell";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs = { self, nixpkgs }:
    let
      systems = [ "x86_64-linux" "aarch64-linux" "x86_64-darwin" "aarch64-darwin" ];
      forAllSystems = nixpkgs.lib.genAttrs systems;
    in
    {
      packages = forAllSystems (system:
        let pkgs = nixpkgs.legacyPackages.${system};
        in {
          default = pkgs.stdenv.mkDerivation {
            pname = "conch";
            version = "0.1.0";
            src = self;

            buildPhase = "make";

            installPhase = ''
              mkdir -p $out/bin
              cp conch $out/bin/
            '';

            meta = with pkgs.lib; {
              description = "A simple, extensible, community focused and customizable UNIX shell";
              homepage = "https://github.com/calheb/conch";
              license = licenses.mit;
              mainProgram = "conch";
              platforms = platforms.unix;
            };
          };
        });
    };
}
