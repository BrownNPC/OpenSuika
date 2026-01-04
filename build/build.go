package main

import (
	"bytes"
	"context"
	"flag"
	"fmt"
	"os"
	"slices"
	"strings"

	"github.com/bitfield/script"
	"github.com/codeclysm/extract"
)

// one of supported_targets
var Target string
var DownloadDeps bool

var Targets = []string{"linux-amd64"}
var supported_targets = strings.ReplaceAll(fmt.Sprint(Targets), " ", ",")

func init() {
	flag.StringVar(&Target, "target", "none", "REQUIRED: --target "+supported_targets)
	flag.BoolVar(&DownloadDeps, "download", false, "Download dependencies before building")
	flag.Parse()
}

func assert(err error, s ...any) {
	if err != nil {
		exit(s...)
	}

}
func exit(s ...any) {
	fmt.Println(s...)
	os.Exit(0)
}
func main() {
	if !slices.Contains(Targets, Target) {
		if Target == "none" {
			exit("--target is required. Pass one of the supported targets:", supported_targets)
		}
		exit("invalid target", Target, "pick one from", supported_targets)
	}
	if DownloadDeps {
		DownloadDependencies(Target)
	}

}
func DownloadDependencies(target string) {
	switch target {
	case "linux-amd64":
		// Download raylib 5.5
		{
			const url = "https://github.com/raysan5/raylib/releases/download/5.5/raylib-5.5_linux_amd64.tar.gz"
			fmt.Println("Downloading raylib 5.5 for linux-amd64")
			b, err := script.Get(url).Bytes()
			assert(err, "failed to download raylib", err)

			err = extract.Gz(context.TODO(), bytes.NewReader(b), "deps/raylib", nil)
			if err != nil {
				fmt.Println(err)
			}
		}
	}
}
