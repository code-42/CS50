from nltk.tokenize import sent_tokenize

# ./compare --lines LittlePrince_HowardTranslation.txt LittlePrince_WoodsTranslation.txt

def lines(a, b):
    # TODO
    # Return lines in both a and b

    # data structures to consider: list, set, ?
    # https://docs.python.org/3/tutorial/datastructures.html
    linesa = []
    linesb = []

    # splitting a string into lines
    # https://docs.python.org/3/library/stdtypes.html#string-methods
    linesa = a.splitlines()
    linesb = b.splitlines()

    # compare two python lists
    # http://appcrawler.com/wordpress/2010/10/22/quick-way-to-compare-two-python-lists/
    return [line for line in linesb if line in linesa]


def sentences(a, b):
    # TODO
    """ Return sentences in both a and b
        split each string into sentences
        make a list of sentences appearing in both a and b
        'Hello there! How are you?' => ['Hello there', 'How are you?']
        use nltk sent_tokenize
        from nltk.tokenize import sent_tokenize
    """
    sentencesa = []
    sentencesb = []

    # splitting a string into sentences
    # https://docs.cs50.net/2018/x/psets/6/similarities/less/similarities.html#code-templates-index-html-code-2
    # from nltk.tokenize import sent_tokenize
    sentencesa = sent_tokenize(a)
    sentencesb = sent_tokenize(b)

    print("same: ")
    return [sentence for sentence in sentencesb if sentence in sentencesa]


def substrings(a, b, n):
    """Return substrings of length n in both a and b
        n is substring length to compare
        split each string into all substrings of length n
        s[i:j] returns s[i] to s[j-1] does not include index j
        write a helper function for s[i:j]
        make a list of all substrings appearing in both a and b
    """

    # TODO
    return []
