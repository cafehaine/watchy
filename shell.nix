{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = with pkgs; [ pkg-config cmake SDL2 glib valgrind helix libclang ];
}

