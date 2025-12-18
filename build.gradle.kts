plugins {
    `cpp-application`
}

group = "hu.bme.vik"
version = "1.0.0"

application {
    baseName.set("szerviz_app")
    source.from(fileTree("src/main/cpp") { include("**/*.cpp") })
    privateHeaders.from(file("src/main/public"))
}

// Compiler and linker settings
tasks.withType<CppCompile>().configureEach {
    compilerArgs.addAll(provider {
        val toolchain = toolChain.get()
        when {
            toolchain.name.contains("gcc") || toolchain.name.contains("clang") -> 
                listOf("-Wall", "-Wextra", "-std=c++11", "-g", "-DMEMTRACE")
            toolchain.name.contains("visualCpp") -> 
                listOf("/W3", "/Zi", "/EHsc", "/DMEMTRACE", "/GR")
            else -> emptyList()
        }
    })
}

// Linker settings
tasks.withType<LinkExecutable>().configureEach {
    linkerArgs.addAll(provider {
        if (toolChain.get().name.contains("visualCpp")) {
            listOf(
                "/DEBUG",
                "/FORCE:MULTIPLE",
                "/OPT:NOREF",
                "ucrt.lib", "vcruntime.lib", "msvcrt.lib"
            )
        } else {
            emptyList()
        }
    })
}

// Post-build action: Copy data files to the output directory for Debug builds
tasks.withType<LinkExecutable>().configureEach {
    doLast {
        val targetDir = linkedFile.get().asFile.parentFile
        
        copy {
            from("data")
            into(targetDir)
        }
        println("✅ Data files copied to: $targetDir")
    }
}