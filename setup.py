from setuptools import setup

setup(
    name='ModDown',
    description='C++ Module Documenter',
    version='1.3',
    author='Tim Simpson',
    license='MIT License',
    packages=['moddown'],
    entry_points={
        'console_scripts': [
            'moddown = moddown.cli:main'
        ],
    },
    install_requires=[
        'MarkdownPP >= 1.3',
    ],
)
