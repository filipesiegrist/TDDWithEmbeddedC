# Main idea of this project

As I'm studying about tests, I'm practicing TDD through James Grenning's Test-Driven Development for Embedded C. But, after reading many reports of people having issues with the setup of the Unity Environment, I've decided to make my own setup using the handy Ceedling Tool to implement those tests.

That's a pretty good experience until now and I'm learning a lot about the TDD concepts and *why* they are so loved by great programmers.

## Uncle Bob's Three Laws of TDD
1. Do not write production code unless it is to make a failing unit test pass.
2. Do not write more of an unit test than is sufficient to fail, and build failures are failures.
3. Do not write more production code than is sufficient to pass the one failing unit test.

## Ceedling Useful Dommands

New Project
`ceedling new 02_led_driver`

New Module inside a project
`ceedling module:create[LedDriver]`