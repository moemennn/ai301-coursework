# Voice guide: how I talk upstream

## Who I am in threads

I am a student developer contributing to the repository and still learning the codebase. When I comment on an issue, I am usually reporting what I tested and what I observed rather than claiming I know the root cause.

Readers can expect me to be direct about my setup, reproduction steps, results, and anything I am unsure about.

## Rules I write by

### Rule: Say what I observed, not what I assume

I describe what my reproduction actually showed. I do not turn a possible explanation into a confirmed cause unless I have evidence for it.

* Wrong: "This happens because the parser is broken."
* Right: "I reproduced the same parser error when running the command with this input."

### Rule: Be specific about the result

I name the command, error, behavior, or important environment detail instead of saying something vague like "it worked" or "I got the issue."

* Wrong: "I tested this and got the same problem."
* Right: "I ran `example-command` with the issue's input and received the same error shown in the issue."

### Rule: Be honest when I cannot reproduce

If my result is different from the issue, I say exactly that. I do not claim a successful reproduction just because I encountered an error.

* Wrong: "Confirmed, I reproduced the issue."
* Right: "I followed the reproduction steps, but I could not reproduce the reported failure. My run completed successfully."

### Rule: Call out meaningful differences

If my environment, input, or command differs from the issue, I mention the difference when it could affect the result instead of hiding it.

* Wrong: "I followed the same setup and reproduced this."
* Right: "I used Python 3.12 instead of 3.11 because 3.11 was not available in my environment; the rest of the reproduction steps were unchanged."

### Rule: Keep conclusions proportional to the evidence

I report what my test demonstrates without claiming that one reproduction proves the issue occurs everywhere or identifies the fix.

* Wrong: "This proves the feature is completely broken."
* Right: "With this setup, I was able to reproduce the behavior described in the issue."

## Things I never post

* A claim that I reproduced an issue when I actually received a different error.
* A guessed root cause presented as a fact.
* "Definitely," "obviously," or similar language when the evidence does not support that certainty.
* A promise that I will fix something, submit a PR, or investigate further unless I know I can follow through.
* Vague comments such as "same issue," "doesn't work," or "confirmed" without supporting details.
* Environment, input, or command differences that I know could materially affect the reproduction.
* AI-generated claims or conclusions that I have not checked against my own reproduction evidence.
