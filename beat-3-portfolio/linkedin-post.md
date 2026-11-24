I opened my first open source pull request, a fix for a rare bug that could make a data storage server quietly hand back the wrong data. The project is OpenGRIS Scaler, an open source tool under FINOS, the financial-services open source foundation, for running large computations across many machines.

To avoid storing duplicates, the server compared a short fingerprint of each piece of data and never the data itself. When two different pieces shared a fingerprint, which is rare but possible, the second was lost without any error.

What I did:
🔎 Proved the bug with a test that forces the rare case to happen
🛠️ Changed the server to compare the actual data whenever fingerprints match
⚠️ Found that my first version created a new crash, and fixed that in its own step before anyone reviewed it
✅ Wrote new tests that failed before my change and pass after it, and ran the project's own checks on my computer, which all passed

The pull request is open and waiting for the maintainers to review it.

The biggest lesson for me: a fix can create a new problem, so I now test the unusual cases on both the old and the new version before I call anything done.

https://github.com/finos/opengris-scaler/pull/1106

#OpenSource #SoftwareEngineering #CPlusPlus
