# progress
A simple header only C++ progress bar.

## Usage
```
Ambasta::ProgressBar progressBar(100, "Super Awesome ProgressBar");
std::chrono::milliseconds duration(200);

for(int i = 0; i < 101; ++i) {
    progressBar.update(i);
    std::this_thread::sleep_for(duration);
}
```
