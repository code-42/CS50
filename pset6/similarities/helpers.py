from nltk.tokenize import sent_tokenize


# https://www.pythoncentral.io/the-odds-ends-of-python-regular-expressions/
def lines(a, b):
    # TODO
    # ./compare --lines LittlePrince_HowardTranslation.txt LittlePrince_WoodsTranslation.txt
    # Return lines in both a and b

    # data structures to consider: list, set, ?
    # https://docs.python.org/3/tutorial/datastructures.html

    # splitting a string into lines
    # https://docs.python.org/3/library/stdtypes.html#string-methods
    linesa = set(a.splitlines())
    linesb = set(b.splitlines())

    # compare two python lists
    # http://appcrawler.com/wordpress/2010/10/22/quick-way-to-compare-two-python-lists/
    return(list(linesa.intersection(linesb)))


def sentences(a, b):
    # TODO
    # ./compare --sentences LittlePrince_HowardTranslation.txt LittlePrince_WoodsTranslation.txt
    """ Return sentences in both a and b
        split each string into sentences
        make a list of sentences appearing in both a and b
        'Hello there! How are you?' => ['Hello there', 'How are you?']
        use nltk sent_tokenize
        from nltk.tokenize import sent_tokenize
    """

    # data structures to consider: list, set, ?
    # https://docs.python.org/3/tutorial/datastructures.html
    sentencesa = []
    sentencesb = []

    # splitting a string into sentences
    # https://docs.cs50.net/2018/x/psets/6/similarities/less/similarities.html#code-templates-index-html-code-2
    # from nltk.tokenize import sent_tokenize
    sentencesa = sent_tokenize(a)
    sentencesb = sent_tokenize(b)

    return [sentence for sentence in sentencesb if sentence in sentencesa]





def substrings(a, b, n):
    # TODO
    # ./compare --substrings 4 candy.txt money.txt
    """Return substrings of length n in both a and b
        n is substring length to compare
        split each string into all substrings of length n
        s[i:j] returns s[i] to s[j-1] does not include index j
        write a helper function for substrings[i:j]
        make a list of all substrings appearing in both a and b
        count(substring):int
        ./compare --substrings 4 candy.txt money.txt
    """

    # data structures to consider: list, set, ?
    # https://docs.python.org/3/tutorial/datastructures.html
    seta = helperFunction(a, n)
    setb = helperFunction(b, n)

    # make a list of all substrings appearing in both a and b
    return(list(seta.intersection(setb)))


# write a helper function for substrings[i:j]
def helperFunction(str, n):

    # data structures to consider: list, set, ?
    # https://docs.python.org/3/tutorial/datastructures.html
    subset = set()

    # store length of a and b in a variable so not calculating on each iteration
    lenstr = len(str)

    # split each string into all substrings of length n
    for i in range(lenstr - n):
        # append each substring to the list
        subset.add(str[i:i + n])

    return subset

