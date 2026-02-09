#[cfg(windows)]
fn main() {
    // Compile Windows stub for risc0-zkvm-platform's sys_alloc_aligned
    cc::Build::new().file("src/zk_precompiles/risc0/windows_stub/sys_alloc.c").compile("risc0_zkvm_platform_stub");
}

#[cfg(not(windows))]
fn main() {}
